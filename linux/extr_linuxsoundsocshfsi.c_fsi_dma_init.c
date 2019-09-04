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
struct fsi_stream {int bus_option; } ;
struct fsi_priv {int dummy; } ;

/* Variables and functions */
 int BUSOP_SET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PACKAGE_16BITBUS_STREAM ; 
 int /*<<< orphan*/  PACKAGE_24BITBUS_BACK ; 

__attribute__((used)) static int fsi_dma_init(struct fsi_priv *fsi, struct fsi_stream *io)
{
	/*
	 * 24bit data : 24bit bus / package in back
	 * 16bit data : 16bit bus / stream mode
	 */
	io->bus_option = BUSOP_SET(24, PACKAGE_24BITBUS_BACK) |
			 BUSOP_SET(16, PACKAGE_16BITBUS_STREAM);

	return 0;
}