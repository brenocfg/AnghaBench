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
typedef  int zip_uint8_t ;
typedef  size_t zip_uint32_t ;
struct zip_string {int* raw; scalar_t__ encoding; size_t length; } ;
typedef  enum zip_encoding_type { ____Placeholder_zip_encoding_type } zip_encoding_type ;

/* Variables and functions */
 int const UTF_8_CONTINUE_MASK ; 
 int const UTF_8_CONTINUE_MATCH ; 
 int const UTF_8_LEN_2_MASK ; 
 int const UTF_8_LEN_2_MATCH ; 
 int const UTF_8_LEN_3_MASK ; 
 int const UTF_8_LEN_3_MATCH ; 
 int const UTF_8_LEN_4_MASK ; 
 int const UTF_8_LEN_4_MATCH ; 
 int ZIP_ENCODING_ASCII ; 
 int ZIP_ENCODING_CP437 ; 
 int ZIP_ENCODING_ERROR ; 
 scalar_t__ ZIP_ENCODING_UNKNOWN ; 
 int ZIP_ENCODING_UTF8_GUESSED ; 
 int ZIP_ENCODING_UTF8_KNOWN ; 

enum zip_encoding_type
_zip_guess_encoding(struct zip_string *str, enum zip_encoding_type expected_encoding)
{
    enum zip_encoding_type enc;
    const zip_uint8_t *name;
    zip_uint32_t i, j, ulen;

    if (str == NULL)
	return ZIP_ENCODING_ASCII;

    name = str->raw;

    if (str->encoding != ZIP_ENCODING_UNKNOWN)
	enc = str->encoding;
    else {
	enc = ZIP_ENCODING_ASCII;
	for (i=0; i<str->length; i++) {
	    if ((name[i] > 31 && name[i] < 128) || name[i] == '\r' || name[i] == '\n' || name[i] == '\t')
		continue;

	    enc = ZIP_ENCODING_UTF8_GUESSED;
	    if ((name[i] & UTF_8_LEN_2_MASK) == UTF_8_LEN_2_MATCH)
		ulen = 1;
	    else if ((name[i] & UTF_8_LEN_3_MASK) == UTF_8_LEN_3_MATCH)
		ulen = 2;
	    else if ((name[i] & UTF_8_LEN_4_MASK) == UTF_8_LEN_4_MATCH)
		ulen = 3;
	    else {
		enc = ZIP_ENCODING_CP437;
		break;
	    }

	    if (i + ulen >= str->length) {
		enc = ZIP_ENCODING_CP437;
		break;
	    }

	    for (j=1; j<=ulen; j++) {
		if ((name[i+j] & UTF_8_CONTINUE_MASK) != UTF_8_CONTINUE_MATCH) {
		    enc = ZIP_ENCODING_CP437;
		    goto done;
		}
	    }
	    i += ulen;
	}
    }

done:
    str->encoding = enc;

    if (expected_encoding != ZIP_ENCODING_UNKNOWN) {
	if (expected_encoding == ZIP_ENCODING_UTF8_KNOWN && enc == ZIP_ENCODING_UTF8_GUESSED)
	    str->encoding = enc = ZIP_ENCODING_UTF8_KNOWN;

	if (expected_encoding != enc && enc != ZIP_ENCODING_ASCII)
	    return ZIP_ENCODING_ERROR;
    }
    
    return enc;
}