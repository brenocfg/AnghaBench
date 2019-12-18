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
typedef  int /*<<< orphan*/  zip_uint16_t ;
struct zip_string {int dummy; } ;
struct zip_error {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ZIP_FL_ENC_GUESS ; 
 int /*<<< orphan*/ * _zip_read_data (int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct zip_error*) ; 
 struct zip_string* _zip_string_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct zip_error*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct zip_string *
_zip_read_string(const zip_uint8_t **buf, FILE *fp, zip_uint16_t len, int nulp, struct zip_error *error)
{
    zip_uint8_t *raw;
    struct zip_string *s;

    if ((raw=_zip_read_data(buf, fp, len, nulp, error)) == NULL)
	return NULL;

    s = _zip_string_new(raw, len, ZIP_FL_ENC_GUESS, error);
    free(raw);
    return s;
}