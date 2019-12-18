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
typedef  size_t HPDF_UINT ;
typedef  int /*<<< orphan*/  HPDF_Stream ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  scalar_t__ HPDF_INT ;
typedef  int HPDF_BYTE ;

/* Variables and functions */
 scalar_t__ HPDF_NEEDS_ESCAPE (int) ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 scalar_t__ HPDF_Stream_Write (int /*<<< orphan*/ ,int*,size_t) ; 
 int HPDF_TEXT_DEFAULT_LEN ; 

HPDF_STATUS
HPDF_Stream_WriteEscapeText2  (HPDF_Stream    stream,
                               const char    *text,
                               HPDF_UINT      len)
{
    char buf[HPDF_TEXT_DEFAULT_LEN];
    HPDF_UINT idx = 0;
    HPDF_INT i;
    const char* p = text;
    HPDF_STATUS ret;

    HPDF_PTRACE((" HPDF_Stream_WriteEscapeText2\n"));

   /* The following block is commented out because it violates "PDF Spec 7.3.4.2 Literal Strings". 
	* It states that the two matching parentheses must still be present to represent an empty 
	* string of zero length. 
	*/
   /*
    if (!len)
        return HPDF_OK;
   */

    buf[idx++] = '(';

    for (i = 0; i < (HPDF_INT)len; i++) {
        HPDF_BYTE c = (HPDF_BYTE)*p++;
        if (HPDF_NEEDS_ESCAPE(c)) {
            buf[idx++] = '\\';

            buf[idx] = (char)(c >> 6);
            buf[idx] += 0x30;
            idx++;
            buf[idx] = (char)((c & 0x38) >> 3);
            buf[idx] += 0x30;
            idx++;
            buf[idx] = (char)(c & 0x07);
            buf[idx] += 0x30;
            idx++;
        }
        else
            buf[idx++] = c;

        if (idx > HPDF_TEXT_DEFAULT_LEN - 4) {
            ret = HPDF_Stream_Write (stream, (HPDF_BYTE *)buf, idx);
            if (ret != HPDF_OK)
                return ret;
            idx = 0;
        }
    }
    buf[idx++] = ')';

    ret = HPDF_Stream_Write (stream, (HPDF_BYTE *)buf, idx);

    return ret;
}