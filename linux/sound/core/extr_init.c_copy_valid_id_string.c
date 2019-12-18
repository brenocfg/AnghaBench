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
struct snd_card {char* id; } ;

/* Variables and functions */
 scalar_t__ isalnum (char const) ; 
 scalar_t__ isalpha (char const) ; 
 scalar_t__ isdigit (char const) ; 

__attribute__((used)) static void copy_valid_id_string(struct snd_card *card, const char *src,
				 const char *nid)
{
	char *id = card->id;

	while (*nid && !isalnum(*nid))
		nid++;
	if (isdigit(*nid))
		*id++ = isalpha(*src) ? *src : 'D';
	while (*nid && (size_t)(id - card->id) < sizeof(card->id) - 1) {
		if (isalnum(*nid))
			*id++ = *nid;
		nid++;
	}
	*id = 0;
}