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
typedef  int /*<<< orphan*/  utf8_char_t ;

/* Variables and functions */
 char* malloc (int) ; 
 double parse_timestamp (char*) ; 
 int /*<<< orphan*/  printf (char*,double) ; 
 int sscanf (int /*<<< orphan*/  const*,char*,char*,char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

void parse_timestamps(const utf8_char_t* line, double* start_pts, double* end_pts, char** cue_settings)
{
    char start_str[32];
    char end_str[32];
    char cue_str[1024];

    int matches = sscanf(line, " %31s --> %31s%1023[^\n\r]", start_str, end_str, cue_str);
    *start_pts = -1;
    *cue_settings = NULL;

    printf("Matches: %d\n", matches);

    if (matches >= 1) {
        *start_pts = parse_timestamp(start_str);
        printf("Start pts: %f\n", *start_pts);
    }
    if (matches >= 2) {
        *end_pts = parse_timestamp(end_str);
    }
    if ((matches == 3) && (strlen(cue_str) > 0)) {
        int cue_size = strlen(cue_str);
        *cue_settings = malloc(cue_size + 1);
        strncpy(*cue_settings, cue_str, cue_size);
        (*cue_settings)[cue_size] = '\0';
    }
}