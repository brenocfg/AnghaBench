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
union vx_codec_data {int /*<<< orphan*/  l; } ;
struct vx_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_CDC_DATA_INIT (union vx_codec_data) ; 
 int /*<<< orphan*/  SET_CDC_DATA_REG (union vx_codec_data,int) ; 
 int /*<<< orphan*/  SET_CDC_DATA_VAL (union vx_codec_data,int) ; 
 int /*<<< orphan*/  vx_write_codec_reg (struct vx_core*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vx_set_codec_reg(struct vx_core *chip, int codec, int reg, int val)
{
	union vx_codec_data data;
	/* DAC control register */
	SET_CDC_DATA_INIT(data);
	SET_CDC_DATA_REG(data, reg);
	SET_CDC_DATA_VAL(data, val);
	vx_write_codec_reg(chip, codec, data.l);
}