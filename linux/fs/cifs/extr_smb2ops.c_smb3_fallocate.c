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
struct file {int dummy; } ;
struct cifs_tcon {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 long EOPNOTSUPP ; 
 int FALLOC_FL_KEEP_SIZE ; 
 int FALLOC_FL_PUNCH_HOLE ; 
 int FALLOC_FL_ZERO_RANGE ; 
 long smb3_punch_hole (struct file*,struct cifs_tcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long smb3_simple_falloc (struct file*,struct cifs_tcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 long smb3_zero_range (struct file*,struct cifs_tcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static long smb3_fallocate(struct file *file, struct cifs_tcon *tcon, int mode,
			   loff_t off, loff_t len)
{
	/* KEEP_SIZE already checked for by do_fallocate */
	if (mode & FALLOC_FL_PUNCH_HOLE)
		return smb3_punch_hole(file, tcon, off, len);
	else if (mode & FALLOC_FL_ZERO_RANGE) {
		if (mode & FALLOC_FL_KEEP_SIZE)
			return smb3_zero_range(file, tcon, off, len, true);
		return smb3_zero_range(file, tcon, off, len, false);
	} else if (mode == FALLOC_FL_KEEP_SIZE)
		return smb3_simple_falloc(file, tcon, off, len, true);
	else if (mode == 0)
		return smb3_simple_falloc(file, tcon, off, len, false);

	return -EOPNOTSUPP;
}