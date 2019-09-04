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
struct SMACK {unsigned int is_nocase; char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  memset (struct SMACK*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char const*) ; 

struct SMACK *
smack_create(const char *name, unsigned nocase)
{
    struct SMACK *smack;

    smack = (struct SMACK *)malloc(sizeof (struct SMACK));
    if (smack == NULL) {
        fprintf(stderr, "%s: out of memory error\n", "smack");
        exit(1);
    }
    memset (smack, 0, sizeof (struct SMACK));

    smack->is_nocase = nocase;
    smack->name = (char*)malloc(strlen(name)+1);
    if (smack->name == NULL) {
        fprintf(stderr, "%s: out of memory error\n", "smack");
        exit(1);
    }
    memcpy(smack->name, name, strlen(name)+1);
    return smack;
}