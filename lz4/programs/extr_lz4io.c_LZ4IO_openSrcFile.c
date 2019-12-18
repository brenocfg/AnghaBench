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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,...) ; 
 int /*<<< orphan*/  SET_BINARY_MODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/  stdinmark ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static FILE* LZ4IO_openSrcFile(const char* srcFileName)
{
    FILE* f;

    if (!strcmp (srcFileName, stdinmark)) {
        DISPLAYLEVEL(4,"Using stdin for input\n");
        f = stdin;
        SET_BINARY_MODE(stdin);
    } else {
        f = fopen(srcFileName, "rb");
        if ( f==NULL ) DISPLAYLEVEL(1, "%s: %s \n", srcFileName, strerror(errno));
    }

    return f;
}