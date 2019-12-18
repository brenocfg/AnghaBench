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
typedef  int jsonsl_uchar_t ;
typedef  TYPE_1__* jsonsl_t ;
struct TYPE_3__ {int pos; } ;

/* Variables and functions */
 int FASTPARSE_BREAK ; 
 int FASTPARSE_EXHAUSTED ; 
 int /*<<< orphan*/  INCR_METRIC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STRINGY_INSIGNIFICANT ; 
 int /*<<< orphan*/  TOTAL ; 
 scalar_t__ is_simple_char (int const) ; 

__attribute__((used)) static int
jsonsl__str_fastparse(jsonsl_t jsn,
                      const jsonsl_uchar_t **bytes_p, size_t *nbytes_p)
{
    const jsonsl_uchar_t *bytes = *bytes_p;
    const jsonsl_uchar_t *end;
    for (end = bytes + *nbytes_p; bytes != end; bytes++) {
        if (
#ifdef JSONSL_USE_WCHAR
                *bytes >= 0x100 ||
#endif /* JSONSL_USE_WCHAR */
                (is_simple_char(*bytes))) {
            INCR_METRIC(TOTAL);
            INCR_METRIC(STRINGY_INSIGNIFICANT);
        } else {
            /* Once we're done here, re-calculate the position variables */
            jsn->pos += (bytes - *bytes_p);
            *nbytes_p -= (bytes - *bytes_p);
            *bytes_p = bytes;
            return FASTPARSE_BREAK;
        }
    }

    /* Once we're done here, re-calculate the position variables */
    jsn->pos += (bytes - *bytes_p);
    return FASTPARSE_EXHAUSTED;
}