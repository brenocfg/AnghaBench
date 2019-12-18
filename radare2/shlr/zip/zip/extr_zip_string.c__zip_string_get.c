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
typedef  char zip_uint8_t ;
typedef  scalar_t__ zip_uint32_t ;
typedef  int zip_flags_t ;
struct zip_string {scalar_t__ encoding; char const* converted; char const* raw; scalar_t__ length; scalar_t__ converted_length; } ;
struct zip_error {int dummy; } ;

/* Variables and functions */
 scalar_t__ ZIP_ENCODING_ASCII ; 
 scalar_t__ ZIP_ENCODING_CP437 ; 
 scalar_t__ ZIP_ENCODING_UNKNOWN ; 
 scalar_t__ ZIP_ENCODING_UTF8_KNOWN ; 
 int ZIP_FL_ENC_RAW ; 
 int ZIP_FL_ENC_STRICT ; 
 char const* _zip_cp437_to_utf8 (char const*,scalar_t__,scalar_t__*,struct zip_error*) ; 
 int /*<<< orphan*/  _zip_guess_encoding (struct zip_string*,scalar_t__) ; 

const zip_uint8_t *
_zip_string_get(struct zip_string *string, zip_uint32_t *lenp, zip_flags_t flags, struct zip_error *error)
{
    static const zip_uint8_t empty[1] = "";

    if (string == NULL) {
	if (lenp)
	    *lenp = 0;
	return empty;
    }

    if ((flags & ZIP_FL_ENC_RAW) == 0) {
	/* start guessing */
	if (string->encoding == ZIP_ENCODING_UNKNOWN)
	    _zip_guess_encoding(string, ZIP_ENCODING_UNKNOWN);

	if (((flags & ZIP_FL_ENC_STRICT)
	     && string->encoding != ZIP_ENCODING_ASCII && string->encoding != ZIP_ENCODING_UTF8_KNOWN)
	    || (string->encoding == ZIP_ENCODING_CP437)) {
	    if (string->converted == NULL) {
		if ((string->converted=_zip_cp437_to_utf8(string->raw, string->length,
							  &string->converted_length, error)) == NULL)
		    return NULL;
	    }
	    if (lenp)
		*lenp = string->converted_length;
	    return string->converted;
	}
    }
    
    if (lenp)
	*lenp = string->length;
    return string->raw;
}