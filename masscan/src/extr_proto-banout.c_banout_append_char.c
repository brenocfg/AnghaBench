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
struct BannerOutput {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  banout_append (struct BannerOutput*,unsigned int,char*,int) ; 

void
banout_append_char(struct BannerOutput *banout, unsigned proto, int c)
{
    char cc = (char)c;
    banout_append(banout, proto, &cc, 1);
}