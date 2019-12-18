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
struct sockmap_options {int drop_expected; } ;
struct msg_stats {int bytes_sent; int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int EIO ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (unsigned char*,int,int,int /*<<< orphan*/ *) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int sendfile (int,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int msg_loop_sendpage(int fd, int iov_length, int cnt,
			     struct msg_stats *s,
			     struct sockmap_options *opt)
{
	bool drop = opt->drop_expected;
	unsigned char k = 0;
	FILE *file;
	int i, fp;

	file = fopen(".sendpage_tst.tmp", "w+");
	for (i = 0; i < iov_length * cnt; i++, k++)
		fwrite(&k, sizeof(char), 1, file);
	fflush(file);
	fseek(file, 0, SEEK_SET);
	fclose(file);

	fp = open(".sendpage_tst.tmp", O_RDONLY);
	clock_gettime(CLOCK_MONOTONIC, &s->start);
	for (i = 0; i < cnt; i++) {
		int sent = sendfile(fd, fp, NULL, iov_length);

		if (!drop && sent < 0) {
			perror("send loop error:");
			close(fp);
			return sent;
		} else if (drop && sent >= 0) {
			printf("sendpage loop error expected: %i\n", sent);
			close(fp);
			return -EIO;
		}

		if (sent > 0)
			s->bytes_sent += sent;
	}
	clock_gettime(CLOCK_MONOTONIC, &s->end);
	close(fp);
	return 0;
}