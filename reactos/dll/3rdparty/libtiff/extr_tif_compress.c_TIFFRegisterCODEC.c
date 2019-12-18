#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  uint16 ;
typedef  int /*<<< orphan*/  tmsize_t ;
struct TYPE_5__ {TYPE_2__* info; struct TYPE_5__* next; } ;
typedef  TYPE_1__ codec_t ;
struct TYPE_6__ {char* name; int /*<<< orphan*/  init; int /*<<< orphan*/  scheme; } ;
typedef  int /*<<< orphan*/  TIFFInitMethod ;
typedef  TYPE_2__ TIFFCodec ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char*,char*,char const*) ; 
 scalar_t__ _TIFFmalloc (int /*<<< orphan*/ ) ; 
 TYPE_1__* registeredCODECS ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

TIFFCodec*
TIFFRegisterCODEC(uint16 scheme, const char* name, TIFFInitMethod init)
{
	codec_t* cd = (codec_t*)
	    _TIFFmalloc((tmsize_t)(sizeof (codec_t) + sizeof (TIFFCodec) + strlen(name)+1));

	if (cd != NULL) {
		cd->info = (TIFFCodec*) ((uint8*) cd + sizeof (codec_t));
		cd->info->name = (char*)
		    ((uint8*) cd->info + sizeof (TIFFCodec));
		strcpy(cd->info->name, name);
		cd->info->scheme = scheme;
		cd->info->init = init;
		cd->next = registeredCODECS;
		registeredCODECS = cd;
	} else {
		TIFFErrorExt(0, "TIFFRegisterCODEC",
		    "No space to register compression scheme %s", name);
		return NULL;
	}
	return (cd->info);
}