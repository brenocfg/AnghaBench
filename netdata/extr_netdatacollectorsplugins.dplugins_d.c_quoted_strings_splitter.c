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
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int quoted_strings_splitter(char *str, char **words, int max_words, int (*custom_isspace)(char)) {
    char *s = str, quote = 0;
    int i = 0, j;

    // skip all white space
    while(unlikely(custom_isspace(*s))) s++;

    // check for quote
    if(unlikely(*s == '\'' || *s == '"')) {
        quote = *s; // remember the quote
        s++;        // skip the quote
    }

    // store the first word
    words[i++] = s;

    // while we have something
    while(likely(*s)) {
        // if it is escape
        if(unlikely(*s == '\\' && s[1])) {
            s += 2;
            continue;
        }

        // if it is quote
        else if(unlikely(*s == quote)) {
            quote = 0;
            *s = ' ';
            continue;
        }

        // if it is a space
        else if(unlikely(quote == 0 && custom_isspace(*s))) {

            // terminate the word
            *s++ = '\0';

            // skip all white space
            while(likely(custom_isspace(*s))) s++;

            // check for quote
            if(unlikely(*s == '\'' || *s == '"')) {
                quote = *s; // remember the quote
                s++;        // skip the quote
            }

            // if we reached the end, stop
            if(unlikely(!*s)) break;

            // store the next word
            if(likely(i < max_words)) words[i++] = s;
            else break;
        }

        // anything else
        else s++;
    }

    // terminate the words
    j = i;
    while(likely(j < max_words)) words[j++] = NULL;

    return i;
}