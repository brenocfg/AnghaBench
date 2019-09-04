#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_ice1712 {int /*<<< orphan*/  card; struct prodigy192_spec* spec; } ;
struct prodigy192_spec {TYPE_1__* ak4114; } ;
struct TYPE_2__ {int /*<<< orphan*/  check_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AK4114_CHECK_NO_RATE ; 
#define  AK4114_DEM0 136 
#define  AK4114_DIF_I24I2S 135 
#define  AK4114_DIT 134 
#define  AK4114_EFH_1024 133 
#define  AK4114_OCKS0 132 
#define  AK4114_OCKS1 131 
#define  AK4114_PWN 130 
#define  AK4114_RST 129 
#define  AK4114_TX1E 128 
 int /*<<< orphan*/  prodigy192_ak4114_read ; 
 int /*<<< orphan*/  prodigy192_ak4114_write ; 
 int snd_ak4114_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char const*,unsigned char const*,struct snd_ice1712*,TYPE_1__**) ; 

__attribute__((used)) static int prodigy192_ak4114_init(struct snd_ice1712 *ice)
{
	static const unsigned char ak4114_init_vals[] = {
		AK4114_RST | AK4114_PWN | AK4114_OCKS0 | AK4114_OCKS1,
		/* ice1724 expects I2S and provides clock,
		 * DEM0 disables the deemphasis filter
		 */
		AK4114_DIF_I24I2S | AK4114_DEM0 ,
		AK4114_TX1E,
		AK4114_EFH_1024 | AK4114_DIT, /* default input RX0 */
		0,
		0
	};
	static const unsigned char ak4114_init_txcsb[] = {
		0x41, 0x02, 0x2c, 0x00, 0x00
	};
	struct prodigy192_spec *spec = ice->spec;
	int err;

	err = snd_ak4114_create(ice->card,
				 prodigy192_ak4114_read,
				 prodigy192_ak4114_write,
				 ak4114_init_vals, ak4114_init_txcsb,
				 ice, &spec->ak4114);
	if (err < 0)
		return err;
	/* AK4114 in Prodigy192 cannot detect external rate correctly.
	 * No reason to stop capture stream due to incorrect checks */
	spec->ak4114->check_flags = AK4114_CHECK_NO_RATE;
	return 0;
}