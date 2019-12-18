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
typedef  int bit32u ;

/* Variables and functions */
 int /*<<< orphan*/  dumpfTell (char*,int) ; 
 int /*<<< orphan*/  fOut ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ ) ; 

void binOut32 ( bit32u Data )
{
// On UNIX machine all 32bit writes need ENDIAN switched
//    Data = EndianSwitch(Data);
//    fwrite( &Data, sizeof(bit32u), 1, fOut);

   char sdat[4];
   int i;

   for(i=0;i<4;i++)
    sdat[i]=(char)(Data>>(i*8));
   fwrite( sdat, 1, 4, fOut);
   dumpfTell("Out32" , Data);
}