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
typedef  int /*<<< orphan*/  u8 ;
struct zr36050 {int /*<<< orphan*/  status1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZR050_STATUS_1 ; 
 int /*<<< orphan*/  zr36050_read (struct zr36050*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8
zr36050_read_status1 (struct zr36050 *ptr)
{
	ptr->status1 = zr36050_read(ptr, ZR050_STATUS_1);

	zr36050_read(ptr, 0);
	return ptr->status1;
}