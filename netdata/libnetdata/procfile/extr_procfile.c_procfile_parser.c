#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* data; size_t len; size_t size; scalar_t__* separators; } ;
typedef  TYPE_1__ procfile ;
typedef  scalar_t__ PF_CHAR_TYPE ;

/* Variables and functions */
 scalar_t__ PF_CHAR_IS_CLOSE ; 
 scalar_t__ PF_CHAR_IS_NEWLINE ; 
 scalar_t__ PF_CHAR_IS_OPEN ; 
 scalar_t__ PF_CHAR_IS_QUOTE ; 
 scalar_t__ PF_CHAR_IS_SEPARATOR ; 
 scalar_t__ PF_CHAR_IS_WORD ; 
 int /*<<< orphan*/  fatal (char*) ; 
 scalar_t__ likely (int) ; 
 size_t* pflines_add (TYPE_1__*) ; 
 int /*<<< orphan*/  pfwords_add (TYPE_1__*,char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void procfile_parser(procfile *ff) {
    // debug(D_PROCFILE, PF_PREFIX ": Parsing file '%s'", ff->filename);

    char  *s = ff->data                 // our current position
        , *e = &ff->data[ff->len]       // the terminating null
        , *t = ff->data;                // the first character of a word (or quoted / parenthesized string)

                                        // the look up array to find our type of character
    PF_CHAR_TYPE *separators = ff->separators;

    char quote = 0;                     // the quote character - only when in quoted string
    size_t opened = 0;                  // counts the number of open parenthesis

    size_t *line_words = pflines_add(ff);

    while(s < e) {
        PF_CHAR_TYPE ct = separators[(unsigned char)(*s)];

        // this is faster than a switch()
        // read more here: http://lazarenko.me/switch/
        if(likely(ct == PF_CHAR_IS_WORD)) {
            s++;
        }
        else if(likely(ct == PF_CHAR_IS_SEPARATOR)) {
            if(!quote && !opened) {
                if (s != t) {
                    // separator, but we have word before it
                    *s = '\0';
                    pfwords_add(ff, t);
                    (*line_words)++;
                    t = ++s;
                }
                else {
                    // separator at the beginning
                    // skip it
                    t = ++s;
                }
            }
            else {
                // we are inside a quote or parenthesized string
                s++;
            }
        }
        else if(likely(ct == PF_CHAR_IS_NEWLINE)) {
            // end of line

            *s = '\0';
            pfwords_add(ff, t);
            (*line_words)++;
            t = ++s;

            // debug(D_PROCFILE, PF_PREFIX ":   ended line %d with %d words", l, ff->lines->lines[l].words);

            line_words = pflines_add(ff);
        }
        else if(likely(ct == PF_CHAR_IS_QUOTE)) {
            if(unlikely(!quote && s == t)) {
                // quote opened at the beginning
                quote = *s;
                t = ++s;
            }
            else if(unlikely(quote && quote == *s)) {
                // quote closed
                quote = 0;

                *s = '\0';
                pfwords_add(ff, t);
                (*line_words)++;
                t = ++s;
            }
            else
                s++;
        }
        else if(likely(ct == PF_CHAR_IS_OPEN)) {
            if(s == t) {
                opened++;
                t = ++s;
            }
            else if(opened) {
                opened++;
                s++;
            }
            else
                s++;
        }
        else if(likely(ct == PF_CHAR_IS_CLOSE)) {
            if(opened) {
                opened--;

                if(!opened) {
                    *s = '\0';
                    pfwords_add(ff, t);
                    (*line_words)++;
                    t = ++s;
                }
                else
                    s++;
            }
            else
                s++;
        }
        else
            fatal("Internal Error: procfile_readall() does not handle all the cases.");
    }

    if(likely(s > t && t < e)) {
        // the last word
        if(unlikely(ff->len >= ff->size)) {
            // we are going to loose the last byte
            s = &ff->data[ff->size - 1];
        }

        *s = '\0';
        pfwords_add(ff, t);
        (*line_words)++;
        // t = ++s;
    }
}