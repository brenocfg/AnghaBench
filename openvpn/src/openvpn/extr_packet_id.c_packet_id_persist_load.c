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
struct packet_id_persist_file_image {int /*<<< orphan*/  id; int /*<<< orphan*/  time; } ;
struct packet_id_persist {int fd; char const* filename; int /*<<< orphan*/  id_last_written; int /*<<< orphan*/  id; int /*<<< orphan*/  time_last_written; int /*<<< orphan*/  time; } ;
struct gc_arena {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  image ;

/* Variables and functions */
 int D_PID_PERSIST ; 
 int /*<<< orphan*/  D_PID_PERSIST_DEBUG ; 
 int LOCK_EX ; 
 int LOCK_NB ; 
 int M_ERR ; 
 int M_ERRNO ; 
 int O_BINARY ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  dmsg (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ flock (int,int) ; 
 int /*<<< orphan*/  gc_free (struct gc_arena*) ; 
 struct gc_arena gc_new () ; 
 int /*<<< orphan*/  msg (int,char*,char const*) ; 
 int /*<<< orphan*/  packet_id_persist_enabled (struct packet_id_persist*) ; 
 int /*<<< orphan*/  packet_id_persist_print (struct packet_id_persist*,struct gc_arena*) ; 
 int platform_open (char const*,int,int) ; 
 int read (int,struct packet_id_persist_file_image*,int) ; 

void
packet_id_persist_load(struct packet_id_persist *p, const char *filename)
{
    struct gc_arena gc = gc_new();
    if (!packet_id_persist_enabled(p))
    {
        /* open packet-id persist file for both read and write */
        p->fd = platform_open(filename,
                              O_CREAT | O_RDWR | O_BINARY,
                              S_IRUSR | S_IWUSR);
        if (p->fd == -1)
        {
            msg(D_PID_PERSIST | M_ERRNO,
                "Cannot open --replay-persist file %s for read/write",
                filename);
        }
        else
        {
            struct packet_id_persist_file_image image;
            ssize_t n;

#if defined(HAVE_FLOCK) && defined(LOCK_EX) && defined(LOCK_NB)
            if (flock(p->fd, LOCK_EX | LOCK_NB))
            {
                msg(M_ERR, "Cannot obtain exclusive lock on --replay-persist file %s", filename);
            }
#endif

            p->filename = filename;
            n = read(p->fd, &image, sizeof(image));
            if (n == sizeof(image))
            {
                p->time = p->time_last_written = image.time;
                p->id = p->id_last_written = image.id;
                dmsg(D_PID_PERSIST_DEBUG, "PID Persist Read from %s: %s",
                     p->filename, packet_id_persist_print(p, &gc));
            }
            else if (n == -1)
            {
                msg(D_PID_PERSIST | M_ERRNO,
                    "Read error on --replay-persist file %s",
                    p->filename);
            }
        }
    }
    gc_free(&gc);
}