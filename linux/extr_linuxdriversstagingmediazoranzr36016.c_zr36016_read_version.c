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
typedef  int u8 ;
struct zr36016 {int version; } ;

/* Variables and functions */
 int zr36016_read (struct zr36016*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8
zr36016_read_version (struct zr36016 *ptr)
{
	ptr->version = zr36016_read(ptr, 0) >> 4;
	return ptr->version;
}