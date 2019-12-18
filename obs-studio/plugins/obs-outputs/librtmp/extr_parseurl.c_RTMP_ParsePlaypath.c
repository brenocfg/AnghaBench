#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* av_val; int av_len; } ;
typedef  TYPE_1__ AVal ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  sscanf (char*,char*,unsigned int*) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 char* strstr (char const*,char*) ; 

void RTMP_ParsePlaypath(AVal *in, AVal *out)
{
    int addMP4 = 0;
    int addMP3 = 0;
    int subExt = 0;
    const char *playpath = in->av_val;
    const char *temp, *q, *ext = NULL;
    const char *ppstart = playpath;
    char *streamname, *destptr, *p;

    int pplen = in->av_len;

    out->av_val = NULL;
    out->av_len = 0;

    if (!playpath)
        return;

    if ((*ppstart == '?') &&
            (temp=strstr(ppstart, "slist=")) != 0)
    {
        ppstart = temp+6;
        pplen = (int)strlen(ppstart);

        temp = strchr(ppstart, '&');
        if (temp)
        {
            pplen = temp-ppstart;
        }
    }

    q = strchr(ppstart, '?');
    if (pplen >= 4)
    {
        if (q)
            ext = q-4;
        else
            ext = &ppstart[pplen-4];
        if ((strncmp(ext, ".f4v", 4) == 0) ||
                (strncmp(ext, ".mp4", 4) == 0))
        {
            addMP4 = 1;
            subExt = 1;
            /* Only remove .flv from rtmp URL, not slist params */
        }
        else if ((ppstart == playpath) &&
                 (strncmp(ext, ".flv", 4) == 0))
        {
            subExt = 1;
        }
        else if (strncmp(ext, ".mp3", 4) == 0)
        {
            addMP3 = 1;
            subExt = 1;
        }
    }

    streamname = (char *)malloc((pplen+4+1)*sizeof(char));
    if (!streamname)
        return;

    destptr = streamname;
    if (addMP4)
    {
        if (strncmp(ppstart, "mp4:", 4))
        {
            strcpy(destptr, "mp4:");
            destptr += 4;
        }
        else
        {
            subExt = 0;
        }
    }
    else if (addMP3)
    {
        if (strncmp(ppstart, "mp3:", 4))
        {
            strcpy(destptr, "mp3:");
            destptr += 4;
        }
        else
        {
            subExt = 0;
        }
    }

    for (p=(char *)ppstart; pplen >0;)
    {
        /* skip extension */
        if (subExt && p == ext)
        {
            p += 4;
            pplen -= 4;
            continue;
        }
        if (*p == '%')
        {
            unsigned int c;
            sscanf(p+1, "%02x", &c);
            *destptr++ = c;
            pplen -= 3;
            p += 3;
        }
        else
        {
            *destptr++ = *p++;
            pplen--;
        }
    }
    *destptr = '\0';

    out->av_val = streamname;
    out->av_len = destptr - streamname;
}