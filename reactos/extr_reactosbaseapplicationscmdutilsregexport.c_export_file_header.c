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
typedef  int WCHAR ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  write_file (int /*<<< orphan*/ ,int const*) ; 

__attribute__((used)) static void export_file_header(HANDLE hFile)
{
    static const WCHAR header[] = { 0xfeff,'W','i','n','d','o','w','s',' ',
                                   'R','e','g','i','s','t','r','y',' ','E','d','i','t','o','r',' ',
                                   'V','e','r','s','i','o','n',' ','5','.','0','0','\r','\n'};

    write_file(hFile, header);
}