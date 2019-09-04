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
typedef  int /*<<< orphan*/  zip_uint8_t ;
typedef  int /*<<< orphan*/  zip_uint64_t ;
typedef  int /*<<< orphan*/  zip_flags_t ;
struct zip_error {int dummy; } ;
struct zip_dirent {int /*<<< orphan*/  filename; } ;
struct zip {int dummy; } ;

/* Variables and functions */
 struct zip_dirent* _zip_get_dirent (struct zip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct zip_error*) ; 
 int /*<<< orphan*/ * _zip_string_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct zip_error*) ; 

const char *
_zip_get_name(struct zip *za, zip_uint64_t idx, zip_flags_t flags, struct zip_error *error)
{
    struct zip_dirent *de;
    const zip_uint8_t *str;

    if ((de=_zip_get_dirent(za, idx, flags, error)) == NULL)
	return NULL;

    if ((str=_zip_string_get(de->filename, NULL, flags, error)) == NULL)
	return NULL;

    return (const char *)str;
}