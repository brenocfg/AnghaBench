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
struct inode {int /*<<< orphan*/  i_private; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mt7601u_eeprom_param_read ; 
 int single_open (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mt7601u_eeprom_param_open(struct inode *inode, struct file *f)
{
	return single_open(f, mt7601u_eeprom_param_read, inode->i_private);
}