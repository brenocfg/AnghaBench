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
struct nfsd4_open {scalar_t__ op_create; scalar_t__ op_createmode; } ;

/* Variables and functions */
 scalar_t__ NFS4_CREATE_EXCLUSIVE4_1 ; 
 scalar_t__ NFS4_CREATE_GUARDED ; 
 scalar_t__ NFS4_CREATE_UNCHECKED ; 
 scalar_t__ NFS4_OPEN_CREATE ; 

__attribute__((used)) static int
is_create_with_attrs(struct nfsd4_open *open)
{
	return open->op_create == NFS4_OPEN_CREATE
		&& (open->op_createmode == NFS4_CREATE_UNCHECKED
		    || open->op_createmode == NFS4_CREATE_GUARDED
		    || open->op_createmode == NFS4_CREATE_EXCLUSIVE4_1);
}