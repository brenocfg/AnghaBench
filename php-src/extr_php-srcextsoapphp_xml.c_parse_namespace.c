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
typedef  int /*<<< orphan*/  xmlChar ;

/* Variables and functions */
 int FALSE ; 
 char* estrdup (char*) ; 
 char* estrndup (char*,int) ; 
 char* strrchr (char*,char) ; 

int parse_namespace(const xmlChar *inval, char **value, char **namespace)
{
	char *found = strrchr((char*)inval, ':');

	if (found != NULL && found != (char*)inval) {
		(*namespace) = estrndup((char*)inval, found - (char*)inval);
		(*value) = estrdup(++found);
	} else {
		(*value) = estrdup((char*)inval);
		(*namespace) = NULL;
	}

	return FALSE;
}