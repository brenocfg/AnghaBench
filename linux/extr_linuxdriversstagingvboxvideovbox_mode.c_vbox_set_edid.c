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
struct edid {int dummy; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_connector_update_edid_property (struct drm_connector*,struct edid*) ; 

__attribute__((used)) static void vbox_set_edid(struct drm_connector *connector, int width,
			  int height)
{
	enum { EDID_SIZE = 128 };
	unsigned char edid[EDID_SIZE] = {
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,	/* header */
		0x58, 0x58,	/* manufacturer (VBX) */
		0x00, 0x00,	/* product code */
		0x00, 0x00, 0x00, 0x00,	/* serial number goes here */
		0x01,		/* week of manufacture */
		0x00,		/* year of manufacture */
		0x01, 0x03,	/* EDID version */
		0x80,		/* capabilities - digital */
		0x00,		/* horiz. res in cm, zero for projectors */
		0x00,		/* vert. res in cm */
		0x78,		/* display gamma (120 == 2.2). */
		0xEE,		/* features (standby, suspend, off, RGB, std */
				/* colour space, preferred timing mode) */
		0xEE, 0x91, 0xA3, 0x54, 0x4C, 0x99, 0x26, 0x0F, 0x50, 0x54,
		/* chromaticity for standard colour space. */
		0x00, 0x00, 0x00,	/* no default timings */
		0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
		    0x01, 0x01,
		0x01, 0x01, 0x01, 0x01,	/* no standard timings */
		0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x06, 0x00, 0x02, 0x02,
		    0x02, 0x02,
		/* descriptor block 1 goes below */
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		/* descriptor block 2, monitor ranges */
		0x00, 0x00, 0x00, 0xFD, 0x00,
		0x00, 0xC8, 0x00, 0xC8, 0x64, 0x00, 0x0A, 0x20, 0x20, 0x20,
		    0x20, 0x20,
		/* 0-200Hz vertical, 0-200KHz horizontal, 1000MHz pixel clock */
		0x20,
		/* descriptor block 3, monitor name */
		0x00, 0x00, 0x00, 0xFC, 0x00,
		'V', 'B', 'O', 'X', ' ', 'm', 'o', 'n', 'i', 't', 'o', 'r',
		'\n',
		/* descriptor block 4: dummy data */
		0x00, 0x00, 0x00, 0x10, 0x00,
		0x0A, 0x20, 0x20, 0x20, 0x20, 0x20,
		0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
		0x20,
		0x00,		/* number of extensions */
		0x00		/* checksum goes here */
	};
	int clock = (width + 6) * (height + 6) * 60 / 10000;
	unsigned int i, sum = 0;

	edid[12] = width & 0xff;
	edid[13] = width >> 8;
	edid[14] = height & 0xff;
	edid[15] = height >> 8;
	edid[54] = clock & 0xff;
	edid[55] = clock >> 8;
	edid[56] = width & 0xff;
	edid[58] = (width >> 4) & 0xf0;
	edid[59] = height & 0xff;
	edid[61] = (height >> 4) & 0xf0;
	for (i = 0; i < EDID_SIZE - 1; ++i)
		sum += edid[i];
	edid[EDID_SIZE - 1] = (0x100 - (sum & 0xFF)) & 0xFF;
	drm_connector_update_edid_property(connector, (struct edid *)edid);
}