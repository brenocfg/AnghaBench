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
struct nfsd_file {int dummy; } ;

/* Variables and functions */
 scalar_t__ nfsd_file_check_write_error (struct nfsd_file*) ; 
 scalar_t__ nfsd_file_check_writeback (struct nfsd_file*) ; 

__attribute__((used)) static bool
nfsd_file_in_use(struct nfsd_file *nf)
{
	return nfsd_file_check_writeback(nf) ||
			nfsd_file_check_write_error(nf);
}