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
struct snd_ice1712 {struct qtet_spec* spec; } ;
struct qtet_spec {unsigned int scr; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int get_scr(struct snd_ice1712 *ice)
{
	struct qtet_spec *spec = ice->spec;
	return spec->scr;
}