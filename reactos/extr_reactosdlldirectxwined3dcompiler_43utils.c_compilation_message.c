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
typedef  int /*<<< orphan*/  va_list ;
struct compilation_messages {int capacity; char* string; int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int MESSAGEBUFFER_INITIAL_SIZE ; 
 int /*<<< orphan*/  TRACE (char*,char*) ; 
 char* d3dcompiler_alloc (int) ; 
 char* d3dcompiler_realloc (char*,int) ; 
 int vsnprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 

void compilation_message(struct compilation_messages *msg, const char *fmt, va_list args)
{
    char* buffer;
    int rc, size;

    if (msg->capacity == 0)
    {
        msg->string = d3dcompiler_alloc(MESSAGEBUFFER_INITIAL_SIZE);
        if (msg->string == NULL)
        {
            ERR("Error allocating memory for parser messages\n");
            return;
        }
        msg->capacity = MESSAGEBUFFER_INITIAL_SIZE;
    }

    while (1)
    {
        rc = vsnprintf(msg->string + msg->size,
                msg->capacity - msg->size, fmt, args);

        if (rc < 0 || rc >= msg->capacity - msg->size)
        {
            size = msg->capacity * 2;
            buffer = d3dcompiler_realloc(msg->string, size);
            if (buffer == NULL)
            {
                ERR("Error reallocating memory for parser messages\n");
                return;
            }
            msg->string = buffer;
            msg->capacity = size;
        }
        else
        {
            TRACE("%s", msg->string + msg->size);
            msg->size += rc;
            return;
        }
    }
}