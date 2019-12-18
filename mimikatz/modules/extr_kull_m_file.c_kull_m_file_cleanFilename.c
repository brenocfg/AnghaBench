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
typedef  int* PWCHAR ;
typedef  size_t DWORD ;

/* Variables and functions */
 size_t ARRAYSIZE (int*) ; 
 int* kull_m_file_forbiddenChars ; 

void kull_m_file_cleanFilename(PWCHAR fileName)
{
	DWORD i, j;
	for(i = 0; fileName[i]; i++)
		for(j = 0; j < ARRAYSIZE(kull_m_file_forbiddenChars); j++)
			if(fileName[i] == kull_m_file_forbiddenChars[j])
				fileName[i] = L'~';
}