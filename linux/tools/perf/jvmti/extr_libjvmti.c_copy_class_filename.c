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

/* Variables and functions */
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 
 int strlen (char const*) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static void
copy_class_filename(const char * class_sign, const char * file_name, char * result, size_t max_length)
{
	/*
	* Assume path name is class hierarchy, this is a common practice with Java programs
	*/
	if (*class_sign == 'L') {
		int j, i = 0;
		char *p = strrchr(class_sign, '/');
		if (p) {
			/* drop the 'L' prefix and copy up to the final '/' */
			for (i = 0; i < (p - class_sign); i++)
				result[i] = class_sign[i+1];
		}
		/*
		* append file name, we use loops and not string ops to avoid modifying
		* class_sign which is used later for the symbol name
		*/
		for (j = 0; i < (max_length - 1) && file_name && j < strlen(file_name); j++, i++)
			result[i] = file_name[j];

		result[i] = '\0';
	} else {
		/* fallback case */
		strlcpy(result, file_name, max_length);
	}
}