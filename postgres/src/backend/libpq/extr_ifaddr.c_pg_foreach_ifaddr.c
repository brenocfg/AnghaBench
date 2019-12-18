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
struct ifreq {int /*<<< orphan*/  ifr_addr; } ;
struct ifconf {char* ifc_buf; size_t ifc_len; struct ifreq* ifc_req; } ;
typedef  scalar_t__ pgsocket ;
typedef  int /*<<< orphan*/  mask ;
typedef  int /*<<< orphan*/  ifc ;
typedef  int /*<<< orphan*/  addr ;
typedef  int /*<<< orphan*/  PgIfAddrCallback ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ EINVAL ; 
 scalar_t__ ENOMEM ; 
 scalar_t__ PGINVALID_SOCKET ; 
 int /*<<< orphan*/  SIOCGIFADDR ; 
 int /*<<< orphan*/  SIOCGIFCONF ; 
 int /*<<< orphan*/  SIOCGIFNETMASK ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int _SIZEOF_ADDR_IFREQ (struct ifreq) ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ ioctl (scalar_t__,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  memcpy (struct ifreq*,struct ifreq*,int) ; 
 int /*<<< orphan*/  memset (struct ifconf*,int /*<<< orphan*/ ,int) ; 
 char* realloc (char*,size_t) ; 
 int /*<<< orphan*/  run_ifaddr_callback (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
pg_foreach_ifaddr(PgIfAddrCallback callback, void *cb_data)
{
	struct ifconf ifc;
	struct ifreq *ifr,
			   *end,
				addr,
				mask;
	char	   *ptr,
			   *buffer = NULL;
	size_t		n_buffer = 1024;
	pgsocket	sock;

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == PGINVALID_SOCKET)
		return -1;

	while (n_buffer < 1024 * 100)
	{
		n_buffer += 1024;
		ptr = realloc(buffer, n_buffer);
		if (!ptr)
		{
			free(buffer);
			close(sock);
			errno = ENOMEM;
			return -1;
		}

		memset(&ifc, 0, sizeof(ifc));
		ifc.ifc_buf = buffer = ptr;
		ifc.ifc_len = n_buffer;

		if (ioctl(sock, SIOCGIFCONF, &ifc) < 0)
		{
			if (errno == EINVAL)
				continue;
			free(buffer);
			close(sock);
			return -1;
		}

		/*
		 * Some Unixes try to return as much data as possible, with no
		 * indication of whether enough space allocated. Don't believe we have
		 * it all unless there's lots of slop.
		 */
		if (ifc.ifc_len < n_buffer - 1024)
			break;
	}

	end = (struct ifreq *) (buffer + ifc.ifc_len);
	for (ifr = ifc.ifc_req; ifr < end;)
	{
		memcpy(&addr, ifr, sizeof(addr));
		memcpy(&mask, ifr, sizeof(mask));
		if (ioctl(sock, SIOCGIFADDR, &addr, sizeof(addr)) == 0 &&
			ioctl(sock, SIOCGIFNETMASK, &mask, sizeof(mask)) == 0)
			run_ifaddr_callback(callback, cb_data,
								&addr.ifr_addr, &mask.ifr_addr);
		ifr = (struct ifreq *) ((char *) ifr + _SIZEOF_ADDR_IFREQ(*ifr));
	}

	free(buffer);
	close(sock);
	return 0;
}