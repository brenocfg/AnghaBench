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
struct md4_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  md4_update (struct md4_ctx*,unsigned char*,int) ; 

__attribute__((used)) static inline void add_char(unsigned char c, struct md4_ctx *md)
{
	md4_update(md, &c, 1);
}