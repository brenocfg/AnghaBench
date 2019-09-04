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
struct zr36050 {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int NO_OF_COMPONENTS ; 
 int /*<<< orphan*/  ZR050_SOS1_IDX ; 
 int /*<<< orphan*/  dprintk (int,char*,int /*<<< orphan*/ ) ; 
 int zr36050_pushit (struct zr36050*,int /*<<< orphan*/ ,int,char*) ; 
 int* zr36050_ta ; 
 int* zr36050_td ; 

__attribute__((used)) static int
zr36050_set_sos (struct zr36050 *ptr)
{
	char sos_data[16];	// max. size of register set
	int i;

	dprintk(3, "%s: write SOS\n", ptr->name);
	sos_data[0] = 0xff;
	sos_data[1] = 0xda;
	sos_data[2] = 0x00;
	sos_data[3] = 2 + 1 + (2 * NO_OF_COMPONENTS) + 3;
	sos_data[4] = NO_OF_COMPONENTS;
	for (i = 0; i < NO_OF_COMPONENTS; i++) {
		sos_data[5 + (i * 2)] = i;	// index
		sos_data[6 + (i * 2)] = (zr36050_td[i] << 4) | zr36050_ta[i];	// AC/DC tbl.sel.
	}
	sos_data[2 + 1 + (2 * NO_OF_COMPONENTS) + 2] = 00;	// scan start
	sos_data[2 + 1 + (2 * NO_OF_COMPONENTS) + 3] = 0x3F;
	sos_data[2 + 1 + (2 * NO_OF_COMPONENTS) + 4] = 00;
	return zr36050_pushit(ptr, ZR050_SOS1_IDX,
			      4 + 1 + (2 * NO_OF_COMPONENTS) + 3,
			      sos_data);
}