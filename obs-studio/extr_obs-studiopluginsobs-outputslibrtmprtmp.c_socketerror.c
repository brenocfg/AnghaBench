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

/* Variables and functions */
 int /*<<< orphan*/  strcpy (char*,char*) ; 

const char *
socketerror(int err)
{
    static char buff[1024];

#ifdef _WIN32
    if (FormatMessageA (FORMAT_MESSAGE_FROM_SYSTEM, NULL, err, 0, buff, sizeof(buff), NULL))
    {
        int i, len;
        buff[sizeof(buff)-1] = '\0';
        len = (int)strlen (buff);
        for (i = 0; i < len; i++)
        {
            if (buff[i] == '\r' || buff[i] == '\n')
            {
                memmove (buff + i, buff + i + 1, len - i);
                i--;
                len--;
            }
        }
        return buff;
    }
#else
    (void)err;
#endif

    strcpy (buff, "unknown error");
    return buff;
}