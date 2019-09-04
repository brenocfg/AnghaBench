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
typedef  scalar_t__ zip_uint32_t ;
typedef  int /*<<< orphan*/  zip_uint16_t ;
struct zip_string {int dummy; } ;
struct zip_extra_field {int dummy; } ;
struct zip_error {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZIP_EF_BOTH ; 
 int /*<<< orphan*/  ZIP_ER_MEMORY ; 
 int /*<<< orphan*/  ZIP_FL_ENC_RAW ; 
 scalar_t__ ZIP_UINT16_MAX ; 
 struct zip_extra_field* _zip_ef_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _zip_error_set (struct zip_error*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _zip_poke4 (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  _zip_string_crc32 (struct zip_string*) ; 
 int /*<<< orphan*/ * _zip_string_get (struct zip_string*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,scalar_t__) ; 

__attribute__((used)) static struct zip_extra_field *
_zip_ef_utf8(zip_uint16_t id, struct zip_string *str, struct zip_error *error)
{
    const zip_uint8_t *raw;
    zip_uint8_t *data, *p;
    zip_uint32_t len;
    struct zip_extra_field *ef;

    raw = _zip_string_get(str, &len, ZIP_FL_ENC_RAW, NULL);

    if (len+5 > ZIP_UINT16_MAX) {
        /* XXX: error */
    }
    
    if ((data=(zip_uint8_t *)malloc(len+5)) == NULL) {
	_zip_error_set(error, ZIP_ER_MEMORY, 0);
	return NULL;
    }

    p = data;
    *(p++) = 1;
    _zip_poke4(_zip_string_crc32(str), &p);
    memcpy(p, raw, len);
    p += len;

    ef = _zip_ef_new(id, (zip_uint16_t)(p-data), data, ZIP_EF_BOTH);
    free(data);
    return ef;
}