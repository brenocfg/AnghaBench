#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* address; scalar_t__ size; } ;
typedef  TYPE_1__ memChunk ;

/* Variables and functions */
 int /*<<< orphan*/  memCopy (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  memFree (TYPE_1__*) ; 
 TYPE_1__* memReserve (long) ; 
 TYPE_1__* memString (char*) ; 
 int /*<<< orphan*/  snprintf (char*,scalar_t__,char*,char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 char* strstr (char*,char*) ; 

void sreplace(char *s,char *orig,char *rep,char multi,long dsize){
	char *p;
	memChunk *buffer,*string,*result;

	if (!(p = strstr (s, orig))) {
		return;
	}

	buffer = memReserve (dsize);
	string = memString (s);

	memCopy (buffer, string);

	snprintf (buffer->address + (p - s), buffer->size - (p - s), "%s%s", rep, p + strlen (orig));

	result = memString (buffer->address);

	strcpy (s,result->address);	//unsafe

	memFree (string);
	memFree (result);
	memFree (buffer);
}