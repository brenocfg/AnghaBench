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
struct TYPE_3__ {char* mime; int type; } ;
typedef  TYPE_1__ phar_mime_type ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int PHAR_MIME_OTHER ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* strrchr (char*,char) ; 
 TYPE_1__* zend_hash_str_find_ptr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int phar_file_type(HashTable *mimes, char *file, char **mime_type) /* {{{ */
{
	char *ext;
	phar_mime_type *mime;
	ext = strrchr(file, '.');
	if (!ext) {
		*mime_type = "text/plain";
		/* no file extension = assume text/plain */
		return PHAR_MIME_OTHER;
	}
	++ext;
	if (NULL == (mime = zend_hash_str_find_ptr(mimes, ext, strlen(ext)))) {
		*mime_type = "application/octet-stream";
		return PHAR_MIME_OTHER;
	}
	*mime_type = mime->mime;
	return mime->type;
}