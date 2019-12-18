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
 int /*<<< orphan*/  r_write_at_be32 (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_write_be32 (void*,int) ; 

__attribute__((used)) static inline void r_write_be64(void *dest, ut64 val) {
	r_write_be32 (dest, val >> 32);
	r_write_at_be32 (dest, (ut32)val, sizeof (ut32));
}