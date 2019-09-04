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
typedef  int /*<<< orphan*/  va_list ;
typedef  int HRESULT ;

/* Variables and functions */
#define  STRSAFE_E_INSUFFICIENT_BUFFER 130 
#define  STRSAFE_E_INVALID_PARAMETER 129 
#define  S_OK 128 
 int StringCchVPrintfEx (char*,size_t,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

int _vsnprintf_s(char *buffer, size_t sizeOfBuffer, size_t count, const char *format, va_list argptr)
{
    size_t cchRemaining;

    HRESULT ret = StringCchVPrintfEx(buffer, sizeOfBuffer, NULL, &cchRemaining, 0, format, argptr);

    // EXAMPLE //////////////////////////
    // -------- > Size of provided buffer in chars (8).
    // ABC0____ > Buffer contents after StringCchVPrintfEx gets called.
    // ---      > What we actually need to return (3).
    //    ----- > Remaining chars in buffer, including post string NULL, returned by StringCchVPrintfEx (5).

    /* _vsnprintf_s returns the number of characters written, not including
       the terminating null, or a negative value if an output error occurs.  */

    switch (ret)
    {
        case S_OK:
            return (sizeOfBuffer - cchRemaining);

        case STRSAFE_E_INVALID_PARAMETER:
        case STRSAFE_E_INSUFFICIENT_BUFFER:
        default:
            return -1;
    }
}