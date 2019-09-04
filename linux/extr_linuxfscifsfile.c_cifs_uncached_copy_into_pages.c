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
struct iov_iter {int /*<<< orphan*/  count; } ;
struct cifs_readdata {int dummy; } ;
struct TCP_Server_Info {int dummy; } ;

/* Variables and functions */
 int uncached_fill_pages (struct TCP_Server_Info*,struct cifs_readdata*,struct iov_iter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cifs_uncached_copy_into_pages(struct TCP_Server_Info *server,
			      struct cifs_readdata *rdata,
			      struct iov_iter *iter)
{
	return uncached_fill_pages(server, rdata, iter, iter->count);
}