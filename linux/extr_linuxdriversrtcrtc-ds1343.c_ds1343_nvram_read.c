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
struct ds1343_priv {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 scalar_t__ DS1343_NVRAM ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,scalar_t__,void*,size_t) ; 

__attribute__((used)) static int ds1343_nvram_read(void *priv, unsigned int off, void *val,
			     size_t bytes)
{
	struct ds1343_priv *ds1343 = priv;

	return regmap_bulk_read(ds1343->map, DS1343_NVRAM + off, val, bytes);
}