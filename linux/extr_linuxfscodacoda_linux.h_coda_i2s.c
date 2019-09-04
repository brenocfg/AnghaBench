#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  c_fid; } ;

/* Variables and functions */
 TYPE_1__* ITOC (struct inode*) ; 
 char* coda_f2s (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline__ char *coda_i2s(struct inode *inode)
{
	return coda_f2s(&(ITOC(inode)->c_fid));
}