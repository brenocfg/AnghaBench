#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16 ;
struct TYPE_8__ {TYPE_1__* info; struct TYPE_8__* next; } ;
typedef  TYPE_2__ codec_t ;
struct TYPE_9__ {scalar_t__ scheme; scalar_t__ name; } ;
struct TYPE_7__ {scalar_t__ scheme; } ;
typedef  TYPE_3__ TIFFCodec ;

/* Variables and functions */
 TYPE_3__* _TIFFBuiltinCODECS ; 
 TYPE_2__* registeredCODECS ; 

const TIFFCodec*
TIFFFindCODEC(uint16 scheme)
{
	const TIFFCodec* c;
	codec_t* cd;

	for (cd = registeredCODECS; cd; cd = cd->next)
		if (cd->info->scheme == scheme)
			return ((const TIFFCodec*) cd->info);
	for (c = _TIFFBuiltinCODECS; c->name; c++)
		if (c->scheme == scheme)
			return (c);
	return ((const TIFFCodec*) 0);
}