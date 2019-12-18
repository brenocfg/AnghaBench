#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int magic_number; int version_major; int version_minor; int snaplen; int /*<<< orphan*/  network; int /*<<< orphan*/  sigfigs; int /*<<< orphan*/  thiszone; } ;
typedef  TYPE_1__ pcap_hdr_t ;
typedef  int /*<<< orphan*/  ghdr ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DLT_IEEE802_11_RADIO ; 
 int /*<<< orphan*/  fwrite (TYPE_1__*,int,int,int /*<<< orphan*/ *) ; 

void write_pcap_header(FILE *o)
{
	pcap_hdr_t ghdr = {
		.magic_number  = 0xa1b2c3d4,
		.version_major = 2,
		.version_minor = 4,
		.thiszone      = 0,
		.sigfigs       = 0,
		.snaplen       = 0xFFFF,
		.network       = DLT_IEEE802_11_RADIO
	};

	fwrite(&ghdr, 1, sizeof(ghdr), o);
}