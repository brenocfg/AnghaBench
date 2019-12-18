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
struct web_client {char separator; int /*<<< orphan*/  url_path_length; } ;

/* Variables and functions */
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  web_client_set_path_query (struct web_client*,char*,char*) ; 

void web_client_split_path_query(struct web_client *w, char *s) {
    //I am assuming here that the separator character(?) is not encoded
    char *ptr = strchr(s, '?');
    if(ptr) {
        w->separator = '?';
        web_client_set_path_query(w, s, ptr);
        return;
    }

    //Here I test the second possibility, the URL is completely encoded by the user.
    //I am not using the strcasestr, because it is fastest to check %3f and compare
    //the next character.
    //We executed some tests with "encodeURI(uri);" described in https://www.w3schools.com/jsref/jsref_encodeuri.asp
    //on July 1st, 2019, that show us that URLs won't have '?','=' and '&' encoded, but we decided to move in front
    //with the next part, because users can develop their own encoded that won't follow this rule.
    char *moveme = s;
    while (moveme) {
        ptr = strchr(moveme, '%');
        if(ptr) {
            char *test = (ptr+1);
            if (!strncmp(test, "3f", 2) || !strncmp(test, "3F", 2)) {
                w->separator = *ptr;
                web_client_set_path_query(w, s, ptr);
                return;
            }
            ptr++;
        }

        moveme = ptr;
    }

    w->separator = 0x00;
    w->url_path_length = strlen(s);
}