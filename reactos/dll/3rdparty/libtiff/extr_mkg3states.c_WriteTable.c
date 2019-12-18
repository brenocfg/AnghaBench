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
struct TYPE_3__ {int State; int Width; scalar_t__ Param; } ;
typedef  TYPE_1__ TIFFFaxTabEnt ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* const_class ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ packoutput ; 
 int /*<<< orphan*/  postbrace ; 
 int prebrace ; 
 char* storage_class ; 

void
WriteTable(FILE* fd, const TIFFFaxTabEnt* T, int Size, const char* name)
{
    int i;
    char* sep;

    fprintf(fd, "%s %s TIFFFaxTabEnt %s[%d] = {",
	storage_class, const_class, name, Size);
    if (packoutput) {
	sep = "\n";
	for (i = 0; i < Size; i++) {
	    fprintf(fd, "%s%s%d,%d,%d%s",
		sep, prebrace, T->State, T->Width, (int) T->Param, postbrace);
	    if (((i+1) % 10) == 0)
		    sep = ",\n";
	    else
		    sep = ",";
	    T++;
	}
    } else {
	sep = "\n ";
	for (i = 0; i < Size; i++) {
	    fprintf(fd, "%s%s%3d,%3d,%4d%s",
		sep, prebrace, T->State, T->Width, (int) T->Param, postbrace);
	    if (((i+1) % 6) == 0)
		    sep = ",\n ";
	    else
		    sep = ",";
	    T++;
	}
    }
    fprintf(fd, "\n};\n");
}