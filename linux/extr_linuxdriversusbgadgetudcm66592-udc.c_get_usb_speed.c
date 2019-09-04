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
typedef  int u16 ;
struct m66592 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M66592_DVSTCTR ; 
 int M66592_RHST ; 
 int m66592_read (struct m66592*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u16 get_usb_speed(struct m66592 *m66592)
{
	return (m66592_read(m66592, M66592_DVSTCTR) & M66592_RHST);
}