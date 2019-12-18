#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  crc; int /*<<< orphan*/  her_znaet_chto; int /*<<< orphan*/  ldaddress; int /*<<< orphan*/  hcs; int /*<<< orphan*/  build_date; int /*<<< orphan*/  filelen; int /*<<< orphan*/  filename; int /*<<< orphan*/  rev_min; int /*<<< orphan*/  rev_maj; int /*<<< orphan*/  control; int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__ ldr_header_t ;

/* Variables and functions */
 char* get_control_info (int /*<<< orphan*/ ) ; 
 int get_hcs (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int reverse_endian16 (int /*<<< orphan*/ ) ; 
 int reverse_endian32 (int /*<<< orphan*/ ) ; 

int dump_header ( ldr_header_t* hd )
{
	printf ( "=== Header Information ===\n" );
	printf ( "Header magic:\t0x%04X\n",reverse_endian16 ( hd->magic ) );
	printf ( "Control:\t0x%04X (%s)\n",reverse_endian16 ( hd->control ), get_control_info ( hd->control ) );
	printf ( "Major rev. :\t0x%04X\n",reverse_endian16 ( hd->rev_maj ) );
	printf ( "Minor rev. :\t0x%04X\n",reverse_endian16 ( hd->rev_min ) );
	printf ( "File name :\t%s\n", ( char* ) &hd->filename );
	printf ( "File length:\t%d bytes\n", reverse_endian32 ( hd->filelen ) );
	printf ( "Build time:\t0x%08X //FixMe: print in human-readable form\n", reverse_endian32 ( hd->build_date ) ); //FixMe:
	printf ( "HCS:\t\t0x%04X  ",reverse_endian16 ( hd->hcs ) );
	uint16_t hcs = get_hcs ( hd );
	int ret=0;
	if ( hcs ==reverse_endian16 ( hd->hcs ) )
	{
		printf ( "(OK!)\n" );
	}
	else
	{
		printf ( "(ERROR! expected 0x%04X)\n",hcs );
		ret=1;
	}
//printf("HCS:\t0x%02X",reverse_endian32(hd->hcs));
	printf ( "Load address:\t0x%08X\n", reverse_endian32 ( hd->ldaddress ) ); //FixMe:
	printf ( "HNW:\t\t0x%04X\n",reverse_endian16 ( hd->her_znaet_chto ) ); //Hell knows what
	printf ( "CRC:\t\t0x%08X\n",reverse_endian32 ( hd->crc ) );
	printf ( "=== Binary Header Dump===\n" );
	int i,j;
	uint8_t* head = ( uint8_t* ) hd;
	for ( i=0;i<=sizeof ( ldr_header_t );i++ )
	{
		if ( i % 8==0 )
			printf ( "\n" );
		printf ( "0x%02x   ",head[i] );
	}
	printf ( "\n\n== End Of Header dump ==\n" );
	return ret;
}