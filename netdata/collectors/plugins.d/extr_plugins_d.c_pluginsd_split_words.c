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
 int /*<<< orphan*/  pluginsd_space ; 
 int quoted_strings_splitter (char*,char**,int,int /*<<< orphan*/ ) ; 

inline int pluginsd_split_words(char *str, char **words, int max_words) {
    return quoted_strings_splitter(str, words, max_words, pluginsd_space);
}