#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* buffer; size_t size; int /*<<< orphan*/  contenttype; } ;
typedef  int /*<<< orphan*/  BUFFER_OVERFLOW_EOF ;
typedef  TYPE_1__ BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  CT_TEXT_PLAIN ; 
 int /*<<< orphan*/  D_WEB_BUFFER ; 
 int /*<<< orphan*/  buffer_overflow_check (TYPE_1__*) ; 
 int /*<<< orphan*/  buffer_overflow_init (TYPE_1__*) ; 
 TYPE_1__* callocz (int,int) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,size_t) ; 
 char* mallocz (size_t) ; 

BUFFER *buffer_create(size_t size)
{
    BUFFER *b;

    debug(D_WEB_BUFFER, "Creating new web buffer of size %zu.", size);

    b = callocz(1, sizeof(BUFFER));
    b->buffer = mallocz(size + sizeof(BUFFER_OVERFLOW_EOF) + 2);
    b->buffer[0] = '\0';
    b->size = size;
    b->contenttype = CT_TEXT_PLAIN;
    buffer_overflow_init(b);
    buffer_overflow_check(b);

    return(b);
}