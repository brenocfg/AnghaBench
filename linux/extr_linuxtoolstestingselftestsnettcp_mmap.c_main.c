#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  on ;
typedef  int /*<<< orphan*/  mss ;
typedef  int /*<<< orphan*/  max_pacing_rate ;

/* Variables and functions */
 unsigned long FILE_SZ ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int MAP_ANONYMOUS ; 
 int MAP_PRIVATE ; 
 int /*<<< orphan*/  MSG_ZEROCOPY ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  PF_INET6 ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_MAX_PACING_RATE ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int /*<<< orphan*/  SO_ZEROCOPY ; 
 int /*<<< orphan*/  TCP_MAXSEG ; 
 int /*<<< orphan*/  apply_rcvsnd_buf (int) ; 
 void* atoi (char*) ; 
 int bind (int,struct sockaddr const*,int) ; 
 int cfg_alen ; 
 int /*<<< orphan*/  cfg_family ; 
 void* cfg_port ; 
 long chunk_size ; 
 int /*<<< orphan*/  close (int) ; 
 int connect (int,struct sockaddr const*,int) ; 
 int /*<<< orphan*/  do_accept (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt (int,char**,char*) ; 
 int keepflag ; 
 int listen (int,int) ; 
 char* mmap (int /*<<< orphan*/ *,long,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (char*,long) ; 
 char* optarg ; 
 int /*<<< orphan*/  perror (char*) ; 
 void* rcvbuf ; 
 long send (int,char*,long,int /*<<< orphan*/ ) ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  setup_sockaddr (int /*<<< orphan*/ ,char*,struct sockaddr_storage*) ; 
 void* sndbuf ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xflg ; 
 int zflg ; 

int main(int argc, char *argv[])
{
	struct sockaddr_storage listenaddr, addr;
	unsigned int max_pacing_rate = 0;
	unsigned long total = 0;
	char *host = NULL;
	int fd, c, on = 1;
	char *buffer;
	int sflg = 0;
	int mss = 0;

	while ((c = getopt(argc, argv, "46p:svr:w:H:zxkP:M:")) != -1) {
		switch (c) {
		case '4':
			cfg_family = PF_INET;
			cfg_alen = sizeof(struct sockaddr_in);
			break;
		case '6':
			cfg_family = PF_INET6;
			cfg_alen = sizeof(struct sockaddr_in6);
			break;
		case 'p':
			cfg_port = atoi(optarg);
			break;
		case 'H':
			host = optarg;
			break;
		case 's': /* server : listen for incoming connections */
			sflg++;
			break;
		case 'r':
			rcvbuf = atoi(optarg);
			break;
		case 'w':
			sndbuf = atoi(optarg);
			break;
		case 'z':
			zflg = 1;
			break;
		case 'M':
			mss = atoi(optarg);
			break;
		case 'x':
			xflg = 1;
			break;
		case 'k':
			keepflag = 1;
			break;
		case 'P':
			max_pacing_rate = atoi(optarg) ;
			break;
		default:
			exit(1);
		}
	}
	if (sflg) {
		int fdlisten = socket(cfg_family, SOCK_STREAM, 0);

		if (fdlisten == -1) {
			perror("socket");
			exit(1);
		}
		apply_rcvsnd_buf(fdlisten);
		setsockopt(fdlisten, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

		setup_sockaddr(cfg_family, host, &listenaddr);

		if (mss &&
		    setsockopt(fdlisten, IPPROTO_TCP, TCP_MAXSEG,
			       &mss, sizeof(mss)) == -1) {
			perror("setsockopt TCP_MAXSEG");
			exit(1);
		}
		if (bind(fdlisten, (const struct sockaddr *)&listenaddr, cfg_alen) == -1) {
			perror("bind");
			exit(1);
		}
		if (listen(fdlisten, 128) == -1) {
			perror("listen");
			exit(1);
		}
		do_accept(fdlisten);
	}
	buffer = mmap(NULL, chunk_size, PROT_READ | PROT_WRITE,
			      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (buffer == (char *)-1) {
		perror("mmap");
		exit(1);
	}

	fd = socket(cfg_family, SOCK_STREAM, 0);
	if (fd == -1) {
		perror("socket");
		exit(1);
	}
	apply_rcvsnd_buf(fd);

	setup_sockaddr(cfg_family, host, &addr);

	if (mss &&
	    setsockopt(fd, IPPROTO_TCP, TCP_MAXSEG, &mss, sizeof(mss)) == -1) {
		perror("setsockopt TCP_MAXSEG");
		exit(1);
	}
	if (connect(fd, (const struct sockaddr *)&addr, cfg_alen) == -1) {
		perror("connect");
		exit(1);
	}
	if (max_pacing_rate &&
	    setsockopt(fd, SOL_SOCKET, SO_MAX_PACING_RATE,
		       &max_pacing_rate, sizeof(max_pacing_rate)) == -1)
		perror("setsockopt SO_MAX_PACING_RATE");

	if (zflg && setsockopt(fd, SOL_SOCKET, SO_ZEROCOPY,
			       &on, sizeof(on)) == -1) {
		perror("setsockopt SO_ZEROCOPY, (-z option disabled)");
		zflg = 0;
	}
	while (total < FILE_SZ) {
		long wr = FILE_SZ - total;

		if (wr > chunk_size)
			wr = chunk_size;
		/* Note : we just want to fill the pipe with 0 bytes */
		wr = send(fd, buffer, wr, zflg ? MSG_ZEROCOPY : 0);
		if (wr <= 0)
			break;
		total += wr;
	}
	close(fd);
	munmap(buffer, chunk_size);
	return 0;
}