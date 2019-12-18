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
typedef  int ut64 ;
typedef  int /*<<< orphan*/  ut32 ;

/* Variables and functions */
 int /*<<< orphan*/  r_write_at_me32 (void*,int,int) ; 
 int /*<<< orphan*/  r_write_me32 (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void r_write_me64(void *dest, ut64 val) {
	r_write_me32 (dest, (ut32)val);
	r_write_at_me32 (dest, val >> 32, sizeof (ut32));
}