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
typedef  int u32 ;
struct fsi_stream {int dummy; } ;
struct fsi_priv {int fmt; } ;
struct fsi_master {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int CR_BWS_16 ; 
 int CR_BWS_24 ; 
 int /*<<< orphan*/  DI_FMT ; 
 int /*<<< orphan*/  DO_FMT ; 
 int /*<<< orphan*/  IN_DMAC ; 
 int /*<<< orphan*/  OUT_DMAC ; 
#define  PACKAGE_16BITBUS_STREAM 130 
#define  PACKAGE_24BITBUS_BACK 129 
#define  PACKAGE_24BITBUS_FRONT 128 
 int VDMD_BACK ; 
 int VDMD_FRONT ; 
 int VDMD_STREAM ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 struct fsi_master* fsi_get_master (struct fsi_priv*) ; 
 int /*<<< orphan*/  fsi_reg_write (struct fsi_priv*,int /*<<< orphan*/ ,int) ; 
 int fsi_stream_is_play (struct fsi_priv*,struct fsi_stream*) ; 
 int fsi_version (struct fsi_master*) ; 

__attribute__((used)) static void fsi_format_bus_setup(struct fsi_priv *fsi, struct fsi_stream *io,
				 u32 bus, struct device *dev)
{
	struct fsi_master *master = fsi_get_master(fsi);
	int is_play = fsi_stream_is_play(fsi, io);
	u32 fmt = fsi->fmt;

	if (fsi_version(master) >= 2) {
		u32 dma = 0;

		/*
		 * FSI2 needs DMA/Bus setting
		 */
		switch (bus) {
		case PACKAGE_24BITBUS_FRONT:
			fmt |= CR_BWS_24;
			dma |= VDMD_FRONT;
			dev_dbg(dev, "24bit bus / package in front\n");
			break;
		case PACKAGE_16BITBUS_STREAM:
			fmt |= CR_BWS_16;
			dma |= VDMD_STREAM;
			dev_dbg(dev, "16bit bus / stream mode\n");
			break;
		case PACKAGE_24BITBUS_BACK:
		default:
			fmt |= CR_BWS_24;
			dma |= VDMD_BACK;
			dev_dbg(dev, "24bit bus / package in back\n");
			break;
		}

		if (is_play)
			fsi_reg_write(fsi, OUT_DMAC,	dma);
		else
			fsi_reg_write(fsi, IN_DMAC,	dma);
	}

	if (is_play)
		fsi_reg_write(fsi, DO_FMT, fmt);
	else
		fsi_reg_write(fsi, DI_FMT, fmt);
}