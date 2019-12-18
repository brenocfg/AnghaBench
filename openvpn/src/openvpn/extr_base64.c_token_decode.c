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
 unsigned int DECODE_ERROR ; 
 scalar_t__ pos (char const) ; 

__attribute__((used)) static unsigned int
token_decode(const char *token)
{
    int i;
    unsigned int val = 0;
    int marker = 0;
    if (!token[0] || !token[1] || !token[2] || !token[3])
    {
        return DECODE_ERROR;
    }
    for (i = 0; i < 4; i++)
    {
        val *= 64;
        if (token[i] == '=')
        {
            marker++;
        }
        else if (marker > 0)
        {
            return DECODE_ERROR;
        }
        else
        {
            val += pos(token[i]);
        }
    }
    if (marker > 2)
    {
        return DECODE_ERROR;
    }
    return (marker << 24) | val;
}