#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* address; } ;
typedef  TYPE_1__ memChunk ;

/* Variables and functions */
 int /*<<< orphan*/  INPUTLINE_BUFFER_REPLACE_SIZE ; 
 int /*<<< orphan*/  memFree (TYPE_1__*) ; 
 TYPE_1__* memReserve (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memStrCat (TYPE_1__*,char*) ; 
 char* mreplace (char*,char*,char*) ; 
 int sscanf (char*,char*,char*) ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 

char *treplace(char *data,char *search,char *replace){
	char *newline,*p;

	memChunk *result,*line;
	//ulong resultAllocSize;

	if (!strlen (search)) {
		return data;
	}

#if MDEBUG2
	DBG ("treplace(string,se,re)","string  : %s",data);
	DBG ("treplace(string,se,re)","search  : %s",search);
	DBG ("treplace(string,se,re)","replace : %s",replace);
#endif

	result = memReserve (INPUTLINE_BUFFER_REPLACE_SIZE);
	line = memReserve (INPUTLINE_BUFFER_REPLACE_SIZE);

	p=data;
	while (sscanf (p, "%[^\n]", line->address) == 1){
		if (p - data > strlen (data)) {
			break;
		}
		newline = mreplace (line->address, search, replace);

		memStrCat (result, newline);
		if (line->address && *(p + strlen (line->address))) {
			memStrCat (result, "\n");
		} else {
			break;
		}

		p += strlen (line->address) + 1;
	}
	p = strdup (result->address);
	memFree (result);
	memFree (line);
	return p;
}