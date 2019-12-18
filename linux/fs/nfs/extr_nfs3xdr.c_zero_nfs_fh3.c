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
struct nfs_fh {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct nfs_fh*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void zero_nfs_fh3(struct nfs_fh *fh)
{
	memset(fh, 0, sizeof(*fh));
}