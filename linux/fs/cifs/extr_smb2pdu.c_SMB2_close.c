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
typedef  int /*<<< orphan*/  u64 ;
struct cifs_tcon {int dummy; } ;

/* Variables and functions */
 int SMB2_close_flags (unsigned int const,struct cifs_tcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
SMB2_close(const unsigned int xid, struct cifs_tcon *tcon,
	   u64 persistent_fid, u64 volatile_fid)
{
	return SMB2_close_flags(xid, tcon, persistent_fid, volatile_fid, 0);
}