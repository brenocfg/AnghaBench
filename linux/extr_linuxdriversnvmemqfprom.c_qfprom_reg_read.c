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
struct qfprom_priv {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  readb (scalar_t__) ; 

__attribute__((used)) static int qfprom_reg_read(void *context,
			unsigned int reg, void *_val, size_t bytes)
{
	struct qfprom_priv *priv = context;
	u8 *val = _val;
	int i = 0, words = bytes;

	while (words--)
		*val++ = readb(priv->base + reg + i++);

	return 0;
}