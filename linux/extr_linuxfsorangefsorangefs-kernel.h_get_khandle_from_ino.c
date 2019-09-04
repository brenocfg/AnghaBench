#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct orangefs_khandle {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_3__ {struct orangefs_khandle khandle; } ;
struct TYPE_4__ {TYPE_1__ refn; } ;

/* Variables and functions */
 TYPE_2__* ORANGEFS_I (struct inode*) ; 

__attribute__((used)) static inline struct orangefs_khandle *get_khandle_from_ino(struct inode *inode)
{
	return &(ORANGEFS_I(inode)->refn.khandle);
}